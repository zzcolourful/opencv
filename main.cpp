#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include "Board.h"

void registerTypes()
{
    qmlRegisterType<Board>("com.example", 1, 0, "DrawingView");

    // 注册一个单例并添加额外的函数
    qmlRegisterSingletonType<Board>(
        "com.example", 1, 0, "DrawingViewSingleton",
        [](QQmlEngine *engine, QJSValue &obj) -> void {
            // 使用 QQmlEngine::rootContext() 创建一个函数来绑定 loadImage
            auto loadImageFunc = [engine](const QString &imagePath) {
                QImage image(imagePath);

                if (!image.isNull()) {
                    // 获取 DrawingView 单例
                    DrawingView *view = qobject_cast<DrawingView*>(engine->rootContext()->contextProperty("drawingView").toQObject());
                    if (view) {
                        view->setBackground(image);
                    }
                }
            };

            // 绑定 loadImage 函数到 QML 上下文中
            obj.setProperty("loadImage", engine->newFunction(loadImageFunc));
        }
    );
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<Board>("MyModule",1,0,"Board");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
