cout << "\nPeriod: " << sub.period << "\n";
        cout << "Price: " << sub.price << "\n";
        cout << "Start Date: " << time_t_to_string(sub.startDate) << "\n";
        cout << "End Date: " << time_t_to_string(sub.endDate) << "\n";
        cout << "Status: " << (sub.active ? "Active" : "Inactive") << "\n";
        cout << "Subscription ID: " << sub.id << "\n";