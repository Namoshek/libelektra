include (LibAddMacros)

add_plugin (network
	SOURCES
		network.h
		network.c
	)

add_plugintest (network ../ipaddr/test_ipaddr.h)
