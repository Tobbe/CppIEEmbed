#include "webformdispatchimpl.h"
#include <locale>
#include "windows.h"
#include "urlcode.h"
#include "webform.h"
#include "jsobject.h"

WebformDispatchImpl::WebformDispatchImpl(JSObject *jsobj)
{
	this->jsobj = jsobj;
}

void WebformDispatchImpl::BeforeNavigate(std::string url, bool *cancel)
{
	static const std::string exconst = "EXECUTE://";
	*cancel = false;

	bool execute = true;
	size_t i = 0;
	while (execute && i < exconst.length()) {
		if (std::toupper(url[i], std::locale()) != exconst[i]) {
			execute = false;
		}

		++i;
	}

	if (execute) {
		std::string command = url.substr(exconst.length());
		if (command[command.length() - 1] == '/') {
			command = command.substr(0, command.length() - 1);
		}

		//MessageBox(NULL, UrlCode::Decode(command).c_str(), "LSExecute", MB_OK);
		//LSExecute(NULL, UrlCode::Decode(command).c_str(), SW_NORMAL);
		// Set Cancel parameter to TRUE to cancel the current event
		*cancel = true;
	}
}

void WebformDispatchImpl::NavigateComplete(std::string url, WebForm *webForm)
{
	webForm->AddCustomObject(jsobj, "JSObject");
}
