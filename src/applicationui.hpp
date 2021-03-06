#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

#include <bb/cascades/Menu>
#include <bb/cascades/Application>
#include <bb/cascades/LocaleHandler>
#include <bb/system/CardDoneMessage.hpp>
#include <bb/system/InvokeManager.hpp>
#include <bb/system/InvokeRequest.hpp>
#include "ODSData.hpp"
#include "ODSSettings.hpp"

namespace bb {
namespace cascades {
class Application;
class LocaleHandler;
}
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI: public QObject {
Q_OBJECT
public:
	ApplicationUI(bb::cascades::Application *app);

	//
	Q_INVOKABLE
	bool isSquare();

	Q_INVOKABLE
    bool isPassport();
	//
	/*
	 * Refreshes the UI with the specified locale
	 *
	 * @param locale - the locale to change to
	 */
	Q_INVOKABLE
	void updateLocale(QString locale);

	//
	Q_INVOKABLE
	QString getCurrentLanguage();

	/*
	 * Allows the current locale to be retrieved from QML
	 *
	 * @return the current locale
	 */
	Q_INVOKABLE
	QString getCurrentLocale();

	/*
	 * Workaround to force keyboard to hide when readonly text area is touched
	 */
	Q_INVOKABLE
	void suppressKeyboard();

	/**
	 * uses Invokation Framework to invoke unbound from URI
	 *
	 */
	Q_INVOKABLE
	void invokeUnbound(QString uri);

	/**
	 * uses Invokation Framework to Invoke bound to MediaPlayer from URI
	 *
	 */
	Q_INVOKABLE
	void invokeBoundMediaPlayer(const QString& uri);

	Q_INVOKABLE
	void invokeBrowser(QString uri);

	Q_INVOKABLE
	void sendMail(const QString title);

	/**
	 * uses Invokation Framework to View the file from URI
	 *
	 */
	Q_INVOKABLE
	void showInView(QString uri);

	/**
	 * uses Invokation Framework to View the file from URI
	 * for a specific MimeType
	 *
	 */
	Q_INVOKABLE
	void showInViewForMimeType(QString uri, QString mimeType);

	/**
	 * uses Invokation Framework to View the file from URI
	 * for a specific target like "sys.pictures.app"
	 *
	 */
	Q_INVOKABLE
	void showInTarget(QString uri, QString target);

	/**
	 * uses Invokation Framework to View the file from URI
	 * for a specific MimeType
	 * and for a specific target like "sys.pictures.app"
	 *
	 */
	Q_INVOKABLE
	void showInTargetForMimeType(QString uri, QString mimeType, QString target);

	/*
	 * login with username and password
	 * true if login credentials are ok
	 */
	Q_INVOKABLE
	void login(QString user, QString pw);

	/**
	 * test if this application
	 * is embedded into client as a Card
	 * from Invocation Framework
	 */
	Q_INVOKABLE
	bool isCard();

	/**
	 * test if this application is running embedded
	 * as a Card, a Viewer or a Service
	 */
	Q_INVOKABLE
	bool isEmbedded();

	Q_INVOKABLE
    bool isWorkPerimeter();

	Q_INVOKABLE
	void startChat(const QString& text);

	Q_INVOKABLE
	void inviteBBM();

	Q_INVOKABLE
	void inviteODS();

	Q_INVOKABLE
	void leaveReview();
	virtual ~ApplicationUI() {
	}
public slots:
// Invoaction
// This method is invoked to notify the invocation system that the action has been done successfully
	void cardDone();
// This method is invoked to notify the invocation system that the action has been done without success
// per ex. Login failed
	void cardCanceled(QString reason);
// slots from AppMenu Sheets:
	void logoutTriggered();
	void aboutTriggered();
	void faqTriggered();
	void feedbackTriggered();
	void helpTriggered();
	void settingsTriggered();
	void onThumbnail();
	void shareTextWithBBM(const QString& text);
	void shareTextWithMail(const QString& text);Q_SIGNALS:
	// The change notification signal of card status change
	void cardStatusChanged();
private slots:
	void onSystemLanguageChanged();
	// ods as target for Invocation Queries
	void handleInvoke(const bb::system::InvokeRequest& request);
	void handleCardResize(const bb::system::CardResizeMessage&);
	void handleCardPooled(const bb::system::CardDoneMessage&);
private:
	Menu* createApplicationMenu();
	HelpActionItem* mHelpItem;
	ActionItem* mFeedbackItem;
	ActionItem* mAboutItem;
	ActionItem* mFAQItem;
	SettingsActionItem* mSettingsItem;
	ActionItem* mLogoutItem;

	QString mCurrentLocale;
	QTranslator* mTranslator;
	bb::cascades::LocaleHandler* mLocaleHandler;
	ODSData* mOdsData;
	ODSSettings* mOdsSettings;

	QString mCardStatus;
	QString mInvokationTarget;
	QString mInvokationSource;
	bool mIsCard;
	bool mIsLaunchedEmbedded;
	bb::system::InvokeManager *mInvokeManager;
	bool mInitialized;

	void translateMenuItems();
	void initTheApplication();
};

#endif /* ApplicationUI_HPP_ */
