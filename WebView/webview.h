#pragma once

#include <QtWidgets/QWidget>
#include "ui_webview.h"

class WebViewPrivate;
class WebView : public QWidget
{
    Q_OBJECT

public:
    WebView(QWidget *parent = Q_NULLPTR);

signals:
    void func(const QString&);

private slots:
    void onTitleChanged(const QString&);
    void on_pushButton_clicked();
private:
    Ui::WebViewClass ui;
    WebViewPrivate *m_pPrivate;
};
