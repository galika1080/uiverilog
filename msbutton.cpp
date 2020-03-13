#include "msbutton.h"

MSButton::MSButton(const QIcon & icon, const QString & text, Module* module_) : QPushButton(icon, text) {
	module = module_;
	QObject::connect(this, SIGNAL(clicked()), this, SLOT(sendClickedWithModule()));
}

void MSButton::sendClickedWithModule() {
	emit clicked_mod(module);
}
