#ifndef QWOSESSIONPROPERTY_H
#define QWOSESSIONPROPERTY_H

#include "qwoglobal.h"

#include <QDialog>
#include <QPointer>
#include <QStandardItemModel>
#include <QItemSelection>

namespace Ui {
class QWoSessionProperty;
}

class QTermWidget;
class QStringListModel;


class QWoSessionProperty : public QDialog
{
    Q_OBJECT
public:
    enum ETypeSession{
      DefaultProperty = 0x1,
      ModifySession = 0x2
    };

    enum EButtonFlag{
        ButtonConnect = 0x1,
        ButtonSave = 0x1 << 1,
        ButtonApplyAll = 0x1 << 2,

        All = ButtonConnect|ButtonSave|ButtonApplyAll
    };


    enum EResult {
        Rejected = QDialog::Rejected,
        Accepted = QDialog::Accepted,
        Connect,
        Save,
        Cancel
    };
    Q_DECLARE_FLAGS(EButtonFlags, EButtonFlag)
public:
    explicit QWoSessionProperty(QWidget *parent = nullptr);
    explicit QWoSessionProperty(const QString& name, QWidget *parent = nullptr);
    virtual ~QWoSessionProperty();

    void setButtonFlags(EButtonFlags flags);
signals:
    void connect(const QString& host);

private slots:
    void onAuthCurrentIndexChanged(const QString & txt);
    void onColorCurrentIndexChanged(const QString & txt);
    void onKeyBindCurrentIndexChanged(const QString & txt);
    void onCurrentFontChanged(const QFont &font);

    void onBlockCursorToggled();
    void onUnderlineCursorToggled();
    void onBeamCursorToggled();

    void onFontValueChanged(int i);

    void onTreeItemClicked(const QModelIndex& index);
    void onIdentifyBrowserClicked();
    void onJumpBrowserClicked();
    void onReadyToConnect();
    void onApplyToAll();
    void onReadyToSave();
    void onSzDirBrowser();
    void onRzDirBrowser();

private:
    void initDefault();
    void initHistory();
    void initCustom();
    void resetProerty(QVariantMap mdata);
    bool saveConfig();
    QString sessionProperty();
    void savePropertyToAll();
    void saveHistory();
    void setFixPreviewString();

private slots:
    void onTimeout();
private:
    QWoSessionProperty(ETypeSession ts, const QString& name, QWidget *parent);
    void init();
private:
    const ETypeSession m_type;
    QString m_name;
    Ui::QWoSessionProperty *ui;
    QStandardItemModel m_model;
    QPointer<QTermWidget> m_preview;
};

#endif // QWOSESSIONPROPERTY_H
