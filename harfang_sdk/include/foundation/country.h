// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {
namespace locale {

struct Info {
	std::string continent, region, country, fips, iso2, iso3;
	int iso;
	std::string internet;
};

// FIPS 10-4: American National Standard Codes for the Representation of Names of Countries, Dependencies, and Areas of Special Sovereignty for Information Interchange.
const Info *GetFIPSCountry(const char *);
// ISO 3166: Two-character.
const Info *GetISO2Country(const char *);
// ISO 3166: Three-character.
const Info *GetISO3Country(const char *);
// ISO 3166: Three-digit.
const Info *GetISOCountry(int);

} // locale
} // gs
