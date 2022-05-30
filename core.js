console.log("Created by 向成渝<x555666777@qq.com>");


;(function (global) {
    if (QWebChannel) {
        new QWebChannel(qt.webChannelTransport, (channel) => {
                            window.__QT_CHANNEL__ = channel;
                        });
    }
})(this);
