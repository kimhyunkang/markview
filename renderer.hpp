#include <string>
#include <wx/stream.h>

extern "C" {
    #include "markdown.h"
    #include "buffer.h"
    #include "html.h"
}

enum RendererErrorType
{
    RIS_IOError,
    RIS_MarkdownError,
    RIS_OutOfMemory,
    RIS_OtherError,
};

// markdown-to-HTML renderer
class MarkdownRenderer
{
public:
    MarkdownRenderer();

    bool render(const char* filename);

    const RendererErrorType getErrType(); 
    const char* getErrMsg();
    const wxString& getData();

private:
    struct sd_callbacks callbacks;
    struct html_renderopt options;

    wxString renderData;

    RendererErrorType errtype;
    char const * errmsg;
};
