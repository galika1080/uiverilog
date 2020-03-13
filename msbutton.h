#pragma once

#include <QPushButton>
#include "module.h"

class MSButton : public QPushButton {
    Q_OBJECT
public:
		MSButton(const QIcon & icon, const QString & text, Module* module);
		Module* module;

public slots:
	void sendClickedWithModule();

signals:
	void clicked_mod(Module* m);
};
