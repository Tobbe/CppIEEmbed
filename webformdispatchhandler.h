#ifndef _WEBFORM_DISPATCH_HANDLER_H__
#define _WEBFORM_DISPATCH_HANDLER_H__

#include <string>

class WebForm;

class WebformDispatchHandler {
public:
	virtual void BeforeNavigate(std::string url, bool *cancel);
	virtual void DocumentComplete(std::string url);
	virtual void NavigateComplete(std::string url, WebForm *webForm);
};

#endif