// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

/// Billing system abstract interface
struct IBilling {
	virtual	~IBilling() {}

	// Process a billing event.
	virtual	void onBillingEvent(const char *event, const char *item) = 0;

	/// Returns true if the platform supports billing.
	virtual	bool isBillingServiceSupported() = 0;
	/// Request a new purchase.
	virtual	bool requestPurchase(const char *) = 0;
	/// Confirm a purchase.
	virtual	bool confirmPurchase(const char *) = 0;
	/// Restore managed purchase states.
	virtual	bool restorePurchases() = 0;
};

} // gs
