#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

/****************************************************************************
** @projectName   OfflineMapTest
** QT Version    5.11.1-5.12.3
** This file is part of the OfflineMapTest project.
** @file          playlistmodel.h
** @brief         Player类中的视频列表播放组件，已经弃用
** @details       Player类中的视频列表播放组件，已经弃用
** @author        wangpengcheng
** @QQ            673018396
** @email         wangpengcheng2018@gmail.com
** @address       https://github.com/wangpengcheng/OfflineMapTest
** @date          2019-06-29 周六  18:42:53
** @example
**
** 示例代码
**
*****************************************************************************/

#include <QAbstractItemModel>
#include <QScopedPointer>
QT_BEGIN_NAMESPACE
class QMediaPlaylist;
QT_END_NAMESPACE
//列表模式
class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    explicit PlaylistModel(QObject *parent = nullptr);
    ~PlaylistModel();
    //行计数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //下标
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QMediaPlaylist *playlist() const;
    void setPlaylist(QMediaPlaylist *playlist);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;

private slots:
    //开始插入元素
    void beginInsertItems(int start, int end);
    //尾部插入元素
    void endInsertItems();
    //开始移除
    void beginRemoveItems(int start, int end);
    //尾部移除
    void endRemoveItems();
    //更改元素
    void changeItems(int start, int end);

private:
    //播放列表元素
    QScopedPointer<QMediaPlaylist> m_playlist;
    QMap<QModelIndex, QVariant> m_data;
};

#endif // PLAYLISTMODEL_H
