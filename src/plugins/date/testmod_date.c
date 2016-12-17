/**
 * @file
 *
 * @brief Tests for date plugin
 *
 * @copyright BSD License (see doc/LICENSE.md or http://www.libelektra.org)
 *
 */

#include <stdlib.h>
#include <string.h>

#include <kdbconfig.h>

#include <tests_plugin.h>


static void testFmt(const char *date, const char *fmt, const short res)
{
    Key *parentKey = keyNew("user/tests/date", KEY_VALUE, "", KEY_END);
    KeySet *ks = ksNew(5, keyNew("user/tests/date/test", KEY_VALUE, date, KEY_META, "check/date", "", KEY_META, "check/date/format", fmt, KEY_END), KS_END);
    KeySet *conf = ksNew(0, KS_END);
    PLUGIN_OPEN("date");
    succeed_if(plugin->kdbGet(plugin, ks, parentKey) == res, "validation failed");
    ksDel(ks);
    keyDel(parentKey);
    PLUGIN_CLOSE ();
}

/*
static void testLocal(const char *date, const short res)
{
    Key *parentKey = keyNew("user/tests/date", KEY_VALUE, "", KEY_END);
    KeySet *ks = ksNew(5, keyNew("user/tests/date/test", KEY_VALUE, date, KEY_META, "check/date", "", KEY_END), KS_END);
    KeySet *conf = ksNew(0, KS_END);
    PLUGIN_OPEN("date");
    succeed_if(plugin->kdbGet(plugin, ks, parentKey) == res, "validation failed");
    ksDel(ks);
    keyDel(parentKey);
    PLUGIN_CLOSE ();

}
*/

static void testIso(const char *date, const char *isoString, const short res)
{
    Key *parentKey = keyNew("user/tests/date", KEY_VALUE, "", KEY_END);
    KeySet *ks = ksNew(5, keyNew("user/tests/date/test", KEY_VALUE, date, KEY_META, "check/date", "", KEY_META, "check/date/iso8601", isoString, KEY_END), KS_END);
    KeySet *conf = ksNew(0, KS_END);
    PLUGIN_OPEN("date");
    succeed_if(plugin->kdbGet(plugin, ks, parentKey) == res, "validation failed");
    ksDel(ks);
    keyDel(parentKey);
    PLUGIN_CLOSE ();
}

int main (int argc, char ** argv)
{
	printf ("DATE     TESTS\n");
	printf ("==================\n\n");

	init (argc, argv);

	testFmt ("20:15:00", "%H:%M:%S", 1);
	testFmt ("20:15:00", "%I:%M:%S", -1);
	testFmt ("Sat 17 Dec 2016 08:07:43 PM CET", "%a %d %b %Y %r %Z", 1);

/*	
	testLocal ("Sat 17 Dec 2016 08:07:43 PM CET", -1);
	testLocal ("Sat Dec 17 20:07:43 2016", 1);
*/

	testIso("2016-12-12T23:59:01Z", "<calendardate>T<time><tz>", 1);
	testIso("2016-12-12T23:59:01Z", "<calendardate>T<time>", -1);
	testIso("2016-12-12T23:59:01Z", "<weekdate>T<time><tz>", -1);
	testIso("2016-W23", "<weekdate>", 1);
	testIso("22:30+04", "<time><tz>", 1);
	testIso("22:30-04", "<time><tz>", 1);

	printf ("\ntestmod_date RESULTS: %d test(s) done. %d error(s).\n", nbTest, nbError);

	return nbError;
}
