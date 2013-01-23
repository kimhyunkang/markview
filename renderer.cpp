extern "C" {
#include <stdio.h>
#include <string.h>
#include <errno.h>
}

#include "renderer.hpp"
#include <wx/strconv.h>

#define READSIZE    4096

MarkdownRenderer::MarkdownRenderer()
    : errmsg(NULL), errtype(RIS_OtherError)
{
    sdhtml_renderer(&callbacks, &options, 0);
}

bool MarkdownRenderer::render(const char* filename)
{
    struct buf* mdbuf = NULL;
    struct buf* htmlbuf = NULL;
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
        return false;
    }

    renderData = wxString(htmlbuf->data, wxConvUTF8, htmlbuf->size);
    bufrelease(htmlbuf);

    return true;
}

const RendererErrorType MarkdownRenderer::getErrType()
{
    return errtype;
}

const char* MarkdownRenderer::getErrMsg()
{
    return errmsg;
}

const wxString& MarkdownRenderer::getData()
{
    return renderData;
}
