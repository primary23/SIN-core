#ifndef INSTASWAP_H
#define INSTASWAP_H

#include "walletmodel.h"

#include <QMenu>
#include <QWidget>

namespace Ui {
class InstaSwap;
}

class ClientModel;
class WalletModel;
class QLineEdit;
class QTableWidget;
class QNetworkReply;
class QNetworkAccessManager;

class InstaSwap : public QWidget
{
    Q_OBJECT

    enum TransactionState {
        awaiting, swaping, withdraw, completed, notcompleted
    };

public:
    explicit InstaSwap(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~InstaSwap();
    void setClientModel(ClientModel* clientModel);
    void setWalletModel(WalletModel* walletModel);
    void setAddress(const QString& address);
    void setAddress(const QString& address, QLineEdit* addrEdit);
    bool validateBitcoinAddress(QString address);

public Q_SLOTS:
    void updateSwapList();
    void showContextMenu(const QPoint&);

private Q_SLOTS:
    void on_addressBookButton_clicked();
    //void on_userButton_clicked();
    void onCopyTransactionActionClicked();
    void onCopyDepositActionClicked();
    void on_depositAmountEdit_textChanged(const QString &arg1);
    void on_receivingAddressEdit_textChanged(const QString &arg1);

    void on_sendSwapButton_clicked();

    void on_allowedPairsCombo_currentIndexChanged(const QString &arg1);

private:
    void showEvent( QShowEvent*  );
    static const char* TransactionStateString[];
    QMenu* swapListContextMenu;
    Ui::InstaSwap *ui;
    ClientModel* clientModel;
    WalletModel* walletModel;
    const PlatformStyle *platformStyle;

    QNetworkAccessManager *ConnectionManager;

    QString PURCHASECOIN;
    QString ENDPOINT;

    void populatePairsCombo();
    void setupSwapList();
    void CopyListColumn( QTableWidget *QTW, int nColumn );

    QJsonDocument callAllowedPairs( );
    QJsonDocument callListHistory( );
    QJsonDocument callTicker( );
    QJsonDocument callDoSwap( );

};

#endif // INSTASWAP_H
