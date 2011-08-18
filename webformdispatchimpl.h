#ifndef _WEBFORM_DISPATCH_IMPL_H__
#define _WEBFORM_DISPATCH_IMPL_H__

#include "webformdispatchhandler.h"

class WebForm;
class JSObject;

class WebformDispatchImpl : public WebformDispatchHandler {
private:
	JSObject *jsobj;
public:
	WebformDispatchImpl(JSObject *jsobj);
	virtual void BeforeNavigate(std::string url, bool *cancel);
	virtual void NavigateComplete(std::string url, WebForm *webForm);
};

#endif