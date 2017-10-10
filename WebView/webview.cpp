#include "webview.h"

#include <QWebEngineView>
#include <QString>
#include <QWebChannel>

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
    int i = 0;
}

WebView::WebView(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.view, &QWebEngineView::titleChanged, this, &WebView::onTitleChange);

    m_pPrivate = new WebViewPrivate(this);
    QWebChannel *pChannel = new QWebChannel(this);
    ui.view->page()->setWebChannel(pChannel);
    pChannel->registerObject("webView", m_pPrivate);

    ui.view->load(QUrl("file///:/WebView/Resources/index.html"));
}

void WebView::onTitleChange(const QString &str)
{
    this->setWindowTitle(str);
}

#include "webview.moc"