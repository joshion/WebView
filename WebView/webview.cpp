#include "webview.h"

#include <QWebEngineView>
#include <QString>
#include <QWebChannel>
#include <QMessageBox>

class WebViewPrivate final : public QObject
{
    Q_OBJECT
friend class WebView;
private:
    WebViewPrivate(QObject *parent = nullptr) {};
    ~WebViewPrivate() {};

public slots:
    void func();

};

void WebViewPrivate::func()
{
    QMessageBox::warning(nullptr, "Qt Warning", "call c++ function from js", QMessageBox::NoButton, QMessageBox::NoButton, QMessageBox::NoButton);
}

WebView::WebView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.view, &QWebEngineView::titleChanged, this, &WebView::onTitleChanged);

    m_pPrivate = new WebViewPrivate(this);
    QWebChannel *pChannel = new QWebChannel(this);
    ui.view->page()->setWebChannel(pChannel);
    pChannel->registerObject("webView", m_pPrivate);

    ui.view->load(QUrl("qrc:/WebView/Resources/index.html"));
}

void WebView::onTitleChanged(const QString &str)
{
    this->setWindowTitle(str);
}

#include "webview.moc"

void WebView::on_pushButton_clicked()
{
    ui.view->page()->runJavaScript("callByCpp()");
}
