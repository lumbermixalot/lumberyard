#include <Cocoa/Cocoa.h>
#include "MacDockIconHandler.h"

#include <QTimer>

@interface DockIconClickEventHandler : NSObject
{
    MacDockIconHandler* dockIconHandler;
}
@end

@implementation DockIconClickEventHandler
- (id)initWithDockIconHandler:(MacDockIconHandler *)aDockIconHandler
{
    self = [super init];
    if (self)
    {
        dockIconHandler = aDockIconHandler;

        [[NSAppleEventManager sharedAppleEventManager]
            setEventHandler:self
                andSelector:@selector(handleDockClickEvent:withReplyEvent:)
              forEventClass:kCoreEventClass
                 andEventID:kAEReopenApplication];
    }
    return self;
}

- (void)handleDockClickEvent:(NSAppleEventDescriptor*)event withReplyEvent:(NSAppleEventDescriptor*)replyEvent
{
    Q_UNUSED(event)
    Q_UNUSED(replyEvent)

    dockIconHandler->dockIconClicked();
}
@end

MacDockIconHandler::MacDockIconHandler(QObject* parent)
    : QObject(parent)
{
    // this has to be delayed, since Qt installs the same handler
    // using 0 is timeout is not enough.
    QTimer* t = new QTimer;
    t->setSingleShot(true);
    t->start(1);
    connect(t, &QTimer::timeout, this, [t, this]()
    {
        NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
        m_dockIconClickEventHandler = [[DockIconClickEventHandler alloc] initWithDockIconHandler:this];
        [pool release];
        t->deleteLater();
    });
}

MacDockIconHandler::~MacDockIconHandler()
{
    [m_dockIconClickEventHandler release];
}

#include <native/utilities/MacDockIconHandler.moc>
