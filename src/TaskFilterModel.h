// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>

#ifndef TASKFILTERMODEL_H
#define TASKFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QtQml/qqmlregistration.h>

// Filters tasks by a free-text query matched against project and task names.
class TaskFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString filterText READ filterText WRITE setFilterText NOTIFY filterTextChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged)

 public:
    explicit TaskFilterModel(QObject *parent = nullptr);

    QString filterText() const;
    void setFilterText(const QString &text);

    int count() const;
    // Number of selected tasks among the visible (filtered) ones.
    int selectedCount() const;

    // Selects or deselects every visible task.
    Q_INVOKABLE void selectAll(bool selected);

 signals:
    void filterTextChanged();
    void countChanged();
    void selectedCountChanged();

 protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

 private:
    void updateCounts();

    QString mFilterText;
    int mCount = 0;
    int mSelectedCount = 0;
};

#endif  // TASKFILTERMODEL_H
