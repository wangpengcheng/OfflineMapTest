#include "MapEngine.h"
#include "GeoMapReply.h"

#include <QtLocation/private/qgeotilespec_p.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>

//-----------------------------------------------------------------------------
GeoTiledMapReply::GeoTiledMapReply(QNetworkAccessManager *networkManager, const QNetworkRequest &request, const QGeoTileSpec &spec, QObject *parent)
    : QGeoTiledMapReply(spec, parent)
    , _reply(NULL)
    , _request(request)
    , _networkManager(networkManager)
{
    if(_request.url().isEmpty()) {//假设没有请求
        if(!_badMapBox.size()) {//设置坏块时的显示标志
            QFile b(":/res/notile.png");
            if(b.open(QFile::ReadOnly))
                _badMapBox = b.readAll();
        }
        setMapImageData(_badMapBox); //设置瓦片Image数据
        setMapImageFormat("png");//设置格式
        setFinished(true);
        setCached(false);
    } else {
        FetchTileTask* task = getMapEngine()->createFetchTileTask(UrlFactory::GaodeSatellite, spec.x(), spec.y(), spec.zoom());//创建请求
        connect(task, &MapTask::error, this, &GeoTiledMapReply::cacheError);//连接请求失败和缓冲错误
        getMapEngine()->addTask(task);     //将任务添加到队列中
    }
}

//-----------------------------------------------------------------------------
GeoTiledMapReply::~GeoTiledMapReply()
{
    if (_reply) {
        _reply->deleteLater();
        _reply = 0;
    }
}
//-----------------------------------------------------------------------------
//重载abort函数
void
GeoTiledMapReply::abort()
{
    if (_reply)
        _reply->abort(); //请求端口
}

//-----------------------------------------------------------------------------
void
GeoTiledMapReply::replyDestroyed()
{
    _reply = 0;
}

//-----------------------------------------------------------------------------
//网络请求结束
void
GeoTiledMapReply::networkReplyFinished()
{
    if (!_reply) {
        return;
    }
    if (_reply->error() != QNetworkReply::NoError) {
        return;
    }
    QByteArray a = _reply->readAll(); //获取图片数据
    setMapImageData(a);               //设置图片数据
    QString format = getMapEngine()->urlFactory()->getImageFormat(UrlFactory::GaodeSatellite, a);   //获取图片格式
    if(!format.isEmpty()) {
        setMapImageFormat(format);
    }
    setFinished(true);
    _reply->deleteLater();
    _reply = 0;
}

//-----------------------------------------------------------------------------
//网络请求错误时的操作
void
GeoTiledMapReply::networkReplyError(QNetworkReply::NetworkError error)
{
    if (!_reply) {
        return;
    }
    if (error != QNetworkReply::OperationCanceledError) {
        qWarning() << "Fetch tile error:" << _reply->errorString();
    }
    _reply->deleteLater();
    _reply = 0;
    if(!_badTile.size()) {
        QFile b(":/res/notile.png");
        if(b.open(QFile::ReadOnly))
            _badTile = b.readAll();
    }
    setMapImageData(_badTile);//设置为请求失败的图片
    setMapImageFormat("png");
    setFinished(true);
    setCached(false);
}

//-----------------------------------------------------------------------------
//缓冲错误时
void
GeoTiledMapReply::cacheError(MapTask::TaskType type, QString /*errorString*/)
{

    if(type != MapTask::taskFetchTile) {
    }
    //-- Tile not in cache. Get it off the Internet.
    //无法在缓存中找到瓦片，就从网络加载
    QNetworkProxy proxy = _networkManager->proxy();
    QNetworkProxy tProxy;
    tProxy.setType(QNetworkProxy::DefaultProxy); //更换端口为默认端口
    _networkManager->setProxy(tProxy);
    _reply = _networkManager->get(_request);
    _reply->setParent(0);
    connect(_reply, SIGNAL(finished()),                         this, SLOT(networkReplyFinished()));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkReplyError(QNetworkReply::NetworkError)));
    connect(_reply, SIGNAL(destroyed()),                        this, SLOT(replyDestroyed()));
    _networkManager->setProxy(proxy);           //端口还原
}

