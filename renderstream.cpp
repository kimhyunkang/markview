extern "C" {
#include <stdio.h>
#include <string.h>
#include <errno.h>
}

#include "renderstream.hpp"

#define READSIZE    4096

RenderingInputStream::RenderingInputStream()
    : htmlbuf(NULL), bufpos(0), errmsg(NULL), errtype(RIS_OtherError)
{
    sdhtml_renderer(&callbacks, &options, 0);
}

RenderingInputStream::~RenderingInputStream()
{
    release();
}

bool RenderingInputStream::render(const char* filename)
{
    struct buf* mdbuf = NULL;
    struct sd_markdown *markdown = NULL;
    int ret;
    FILE* stream = fopen(filename, "r");

    if(!stream)  {
        errtype = RIS_IOError;
        errmsg = strerror(errno);
        return false;
    }

    mdbuf = bufnew(READSIZE);

    if(!mdbuf || bufgrow(mdbuf, READSIZE) != BUF_OK) {
        errtype = RIS_OutOfMemory;
        errmsg = strerror(ENOMEM);
        fclose(stream);
        return false;
    }

    while ((ret = fread(mdbuf->data + mdbuf->size, 1, mdbuf->asize - mdbuf->size, stream)) > 0) {
        mdbuf->size += ret;
        if(bufgrow(mdbuf, mdbuf->size + READSIZE) != BUF_OK) {
            errtype = RIS_OutOfMemory;
            errmsg = strerror(ENOMEM);
            fclose(stream);
            return false;
        }
    }

    fclose(stream);

    release();
    htmlbuf = bufnew(READSIZE);

    if(!htmlbuf) {
        errtype = RIS_OutOfMemory;
        errmsg = strerror(ENOMEM);
        bufrelease(mdbuf);
        return false;
    }

    markdown = sd_markdown_new(0, 16, &callbacks, &options);
    sd_markdown_render(htmlbuf, mdbuf->data, mdbuf->size, markdown);
    bufrelease(mdbuf);

    if(htmlbuf->size == 0) {
        errtype = RIS_MarkdownError;
        errmsg = "Rendering failed";
        release();
        return false;
    }

    bufpos = 0;
    return true;
}

void RenderingInputStream::release()
{
    if(htmlbuf) {
        bufrelease(htmlbuf);
        htmlbuf = NULL;
        bufpos = 0;
    }
}

size_t RenderingInputStream::OnSysRead(void *buffer, size_t bufsize)
{
    size_t copysize;

    if(!htmlbuf) {
        return 0;
    }

    copysize = htmlbuf->size - bufpos;
    if(copysize <= 0 || bufsize <= 0) {
        return 0;
    }

    if(bufsize < copysize) {
        copysize = bufsize;
    }

    memcpy(buffer, (void *)(htmlbuf->data + bufpos), copysize);
    bufpos += copysize;

    return copysize;
}


const RenderingInputStreamErrorType RenderingInputStream::getErrType()
{
    return errtype;
}

const char* RenderingInputStream::getErrMsg()
{
    return errmsg;
}
