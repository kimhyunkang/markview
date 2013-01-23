#include <string>
#include <wx/stream.h>

extern "C" {
    #include "markdown.h"
    #include "buffer.h"
    #include "html.h"
}

enum RenderingInputStreamErrorType
{
    RIS_IOError,
    RIS_MarkdownError,
    RIS_OutOfMemory,
    RIS_OtherError,
};

// markdown-to-HTML renderer
class RenderingInputStream : public wxInputStream
{
public:
    RenderingInputStream();
    virtual ~RenderingInputStream();

    bool render(const char* filename);

    const RenderingInputStreamErrorType getErrType(); 
    const char* getErrMsg();

protected:
    virtual size_t OnSysRead(void *buffer, size_t bufsize);

    void release();

private:
    struct sd_callbacks callbacks;
    struct html_renderopt options;

    struct buf *htmlbuf;
    size_t bufpos;

    RenderingInputStreamErrorType errtype;
    char* errmsg;
};
