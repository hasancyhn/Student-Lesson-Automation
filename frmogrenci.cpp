#include "frmogrenci.h"

frmOgrenci::frmOgrenci(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant frmOgrenci::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex frmOgrenci::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex frmOgrenci::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int frmOgrenci::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int frmOgrenci::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant frmOgrenci::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
