/*
 * Account.cpp
 *
 * Implementation File
 *
 *  Created on: Nov 17, 2015
 *      Author: Brett
 */

#include "Account.h"

bool Account::withdraw(double amount)
{
	if(balance < amount)
	{
		return false;
	}
	else
	{
		balance -= amount;
		transactions++;
		return true;
	}
}

