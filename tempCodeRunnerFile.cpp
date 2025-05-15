DataManager dataManager;
    dataManager.loadData();

    ClassManager classManager(dataManager);
    CourtBookingManager courtBookingManager(dataManager);
    NotificationManager notificationManager(dataManager);
    SubscriptionManager subscriptionManager(dataManager);

    classManager.load_member_classes();
    courtBookingManager.load_member_court_bookings();
    notificationManager.load_member_notifications();

    User temp(dataManager);
    temp.login();

    if (!temp.getLoggedInMember().id.empty())
    {
        // A member is logged in
        Member loggedInMember = temp.getLoggedInMember();
        subscriptionManager.load_member_subscriptions(loggedInMember, notificationManager);