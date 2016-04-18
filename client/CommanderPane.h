#ifndef COMMANDERPANE_H
#define COMMANDERPANE_H

#include <map>
#include <QWidget>
#include <QTabWidget>
#include <QScrollArea>
#include "clienttypes.h"
#include "BasicLandCardDataMap.h"
#include "BasicLandQuantities.h"

QT_BEGIN_NAMESPACE
class QStackedWidget;
class QBoxLayout;
QT_END_NAMESPACE

class CardData;
class CardViewerWidget;
class ImageLoaderFactory;
class BasicLandControlWidget;
class DraftTimerWidget;
class CommanderPane_TabWidget;

// This allows our custom types to be passed around in QVariant types
// with comboboxes.
Q_DECLARE_METATYPE( CardCategorizationType );
Q_DECLARE_METATYPE( CardSortCriterionVector );

#include "Logging.h"

// "Midnight Commander" widget.  Handles a single side of the interface; i.e.
// create two of these and hook them together to make an MC-like setup.
class CommanderPane : public QWidget
{
    Q_OBJECT

public:
    explicit CommanderPane( const std::vector<CardZoneType>& cardZones,
                            ImageLoaderFactory*              imageLoaderFactory,
                            const Logging::Config&           loggingConfig = Logging::Config(),
                            QWidget*                         parent = 0 );

    CardZoneType getCurrentCardZone() const { return mCurrentCardZone; }

    void setBasicLandCardDataMap( const BasicLandCardDataMap& val );

signals:

    // move card requested via right-click menu or other
    void cardZoneMoveRequest( const CardZoneType& srcCardZone, const CardDataSharedPtr& cardData, const CardZoneType& destCardZone );

    // move all requested via right-click menu or other
    void cardZoneMoveAllRequest( const CardZoneType& srcCardZone, const CardZoneType& destCardZone );

    // pre-selected via single-click
    void cardPreselected( const CardZoneType& srcCardZone, const CardDataSharedPtr& cardData );

    // selected via double-click
    void cardSelected( const CardZoneType& srcCardZone, const CardDataSharedPtr& cardData );

    // basic land quantities updated
    void basicLandQuantitiesUpdate( const CardZoneType& srcCardZone, const BasicLandQuantities& basicLandQtys );

public slots:

    // Set card list for a zone in this pane.
    void setCards( const CardZoneType& cardZone, const QList<CardDataSharedPtr>& cards );

    // Update basic land quantities for a zone in this pane.
    void setBasicLandQuantities( const CardZoneType& cardZone, const BasicLandQuantities& basicLandQtys );

    // Set draft packs queued; set to -1 if the queue should be inactive.
    void setDraftQueuedPacks( int count );

    // Set draft tick count; set to -1 if the counter should be inactive.
    void setDraftTickCount( int count );

    // Set true to make the pane alert the user to an urgent draft event.
    void setDraftAlert( bool alert );

private slots:

    void handleCardDoubleClicked( const CardDataSharedPtr& cardData );
    void handleCardShiftClicked( const CardDataSharedPtr& cardData );
    void handleCardContextMenu( const CardDataSharedPtr& cardData, const QPoint& pos );
    void handleViewerContextMenu( const QPoint& pos );
    void handleZoomComboBoxChange( int index );
    void handleCategorizationComboBoxChange( int index );
    void handleSortComboBoxChange( int index );

private:

    void updateTabTitle( const CardZoneType& cardZone );
    bool isBasicLandCardData( const CardDataSharedPtr& cardData, BasicLandType& basicOut );

private:

    CardZoneType mCurrentCardZone;
    ImageLoaderFactory* mImageLoaderFactory;

    QStackedWidget* mStackedWidget;
    CommanderPane_TabWidget* mCardViewerTabWidget;
    std::map<CardZoneType,CardViewerWidget*> mCardViewerWidgetMap;
    std::map<CardZoneType,BasicLandControlWidget*> mBasicLandControlWidgetMap;
    std::map<int,CardZoneType> mTabIndexToCardZoneMap;
    std::map<CardZoneType,int> mCardZoneToTabIndexMap;

    DraftTimerWidget* mDraftTimerWidget;
    QBoxLayout* mDraftPackQueueLayout;
    int mDraftPackQueueSize;
    QColor mDefaultDraftTabTextColor;

    QSize mDefaultUnloadedSize;

    BasicLandCardDataMap mBasicLandCardDataMap;

    Logging::Config                 mLoggingConfig;
    std::shared_ptr<spdlog::logger> mLogger;
};


//
// Subclasses of internal widgets with minor overrides for behavior.
// Would be nested classes but the Q_OBJECT macro doesn't work.
//


class CommanderPane_TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    CommanderPane_TabWidget( QWidget* parent = 0 ) : QTabWidget( parent ) {}

    // Publicize protected method from QTabWidget.
    QTabBar* tabBar() const
    {
        return QTabWidget::tabBar();
    }
};;


class CommanderPane_CardScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    CommanderPane_CardScrollArea( QWidget* parent = 0 ) : QScrollArea( parent ) {}
protected:
    virtual QSize sizeHint() const override
    {
        return QSize( 750, 600 );
    }
};


#endif  // COMMANDERPANE_H