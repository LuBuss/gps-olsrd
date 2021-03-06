# cmake_minimum_required(VERSION <specify CMake version here>)
project(olsrd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    contrib/netsimpcap/src/config.c
    contrib/netsimpcap/src/config.h
    contrib/netsimpcap/src/debug.h
    contrib/netsimpcap/src/netsimpcap.c
    contrib/netsimpcap/src/network_tap.c
    contrib/netsimpcap/src/network_tap.h
    contrib/netsimpcap/LICENCE
    contrib/netsimpcap/Makefile
    contrib/netsimpcap/sampleconf.txt
    contrib/README
    lib/arprefresh/src/olsrd_arprefresh.c
    lib/arprefresh/src/olsrd_arprefresh.h
    lib/bmf/src/Address.c
    lib/bmf/src/Address.h
    lib/bmf/src/Bmf.c
    lib/bmf/src/Bmf.h
    lib/bmf/src/NetworkInterfaces.c
    lib/bmf/src/NetworkInterfaces.h
    lib/bmf/src/olsrd_plugin.c
    lib/bmf/src/Packet.c
    lib/bmf/src/Packet.h
    lib/bmf/src/PacketHistory.c
    lib/bmf/src/PacketHistory.h
    lib/dot_draw/src/olsrd_dot_draw.c
    lib/dot_draw/src/olsrd_dot_draw.h
    lib/dot_draw/src/olsrd_plugin.c
    lib/dyn_gw/src/olsrd_dyn_gw.c
    lib/dyn_gw/src/olsrd_dyn_gw.h
    lib/dyn_gw/src/olsrd_plugin.c
    lib/dyn_gw_plain/src/olsrd_dyn_gw_plain.c
    lib/dyn_gw_plain/src/olsrd_dyn_gw_plain.h
    lib/httpinfo/src/admin_interface.c
    lib/httpinfo/src/admin_interface.h
    lib/httpinfo/src/gfx.h
    lib/httpinfo/src/olsrd_httpinfo.c
    lib/httpinfo/src/olsrd_httpinfo.h
    lib/httpinfo/src/olsrd_plugin.c
    lib/httpinfo/src/olsrd_plugin.h
    lib/info/http_headers.c
    lib/info/http_headers.h
    lib/info/info_types.h
    lib/info/json_helpers.c
    lib/info/json_helpers.h
    lib/info/olsrd_info.c
    lib/info/olsrd_info.h
    lib/jsoninfo/src/olsrd_jsoninfo.c
    lib/jsoninfo/src/olsrd_jsoninfo.h
    lib/jsoninfo/src/olsrd_plugin.c
    lib/jsoninfo/src/olsrd_plugin.h
    lib/mdns/src/Address.c
    lib/mdns/src/Address.h
    lib/mdns/src/container_of.h
    lib/mdns/src/list_backport.h
    lib/mdns/src/mdns.c
    lib/mdns/src/mdns.h
    lib/mdns/src/NetworkInterfaces.c
    lib/mdns/src/NetworkInterfaces.h
    lib/mdns/src/olsrd_plugin.c
    lib/mdns/src/Packet.c
    lib/mdns/src/Packet.h
    lib/mdns/src/RouterElection.c
    lib/mdns/src/RouterElection.h
    lib/mini/src/mini_plugin.c
    lib/mini/src/mini_plugin.h
    lib/nameservice/src/compat.c
    lib/nameservice/src/compat.h
    lib/nameservice/src/mapwrite.c
    lib/nameservice/src/mapwrite.h
    lib/nameservice/src/nameservice.c
    lib/nameservice/src/nameservice.h
    lib/nameservice/src/nameservice_msg.h
    lib/nameservice/src/olsrd_plugin.c
    lib/netjson/src/olsrd_netjson.c
    lib/netjson/src/olsrd_netjson.h
    lib/netjson/src/olsrd_netjson_helpers.c
    lib/netjson/src/olsrd_netjson_helpers.h
    lib/netjson/src/olsrd_plugin.c
    lib/netjson/src/olsrd_plugin.h
    lib/p2pd/src/dllist.c
    lib/p2pd/src/dllist.h
    lib/p2pd/src/NetworkInterfaces.c
    lib/p2pd/src/NetworkInterfaces.h
    lib/p2pd/src/olsrd_plugin.c
    lib/p2pd/src/p2pd.c
    lib/p2pd/src/p2pd.h
    lib/p2pd/src/Packet.c
    lib/p2pd/src/Packet.h
    lib/p2pd/src/PacketHistory.c
    lib/p2pd/src/PacketHistory.h
    lib/pgraph/src/olsrd_pgraph.c
    lib/pgraph/src/olsrd_pgraph.h
    lib/pud/nmealib/include/nmea/context.h
    lib/pud/nmealib/include/nmea/conversions.h
    lib/pud/nmealib/include/nmea/generate.h
    lib/pud/nmealib/include/nmea/generator.h
    lib/pud/nmealib/include/nmea/gmath.h
    lib/pud/nmealib/include/nmea/info.h
    lib/pud/nmealib/include/nmea/parse.h
    lib/pud/nmealib/include/nmea/parser.h
    lib/pud/nmealib/include/nmea/sentence.h
    lib/pud/nmealib/include/nmea/tok.h
    lib/pud/nmealib/src/context.c
    lib/pud/nmealib/src/conversions.c
    lib/pud/nmealib/src/generate.c
    lib/pud/nmealib/src/generator.c
    lib/pud/nmealib/src/gmath.c
    lib/pud/nmealib/src/info.c
    lib/pud/nmealib/src/parse.c
    lib/pud/nmealib/src/parser.c
    lib/pud/nmealib/src/random.h
    lib/pud/nmealib/src/sentence.c
    lib/pud/nmealib/src/tok.c
    lib/pud/src/compiler.h
    lib/pud/src/configTools.c
    lib/pud/src/configTools.h
    lib/pud/src/configuration.c
    lib/pud/src/configuration.h
    lib/pud/src/dedup.c
    lib/pud/src/dedup.h
    lib/pud/src/gpsConversion.c
    lib/pud/src/gpsConversion.h
    lib/pud/src/netTools.c
    lib/pud/src/netTools.h
    lib/pud/src/networkInterfaces.c
    lib/pud/src/networkInterfaces.h
    lib/pud/src/posAvg.c
    lib/pud/src/posAvg.h
    lib/pud/src/posFile.c
    lib/pud/src/posFile.h
    lib/pud/src/pud.c
    lib/pud/src/pud.h
    lib/pud/src/pudOlsrdPlugin.c
    lib/pud/src/pudOlsrdPlugin.h
    lib/pud/src/receiver.c
    lib/pud/src/receiver.h
    lib/pud/src/state.c
    lib/pud/src/state.h
    lib/pud/src/timers.c
    lib/pud/src/timers.h
    lib/pud/src/uplinkGateway.c
    lib/pud/src/uplinkGateway.h
    lib/pud/wireformat/include/OlsrdPudWireFormat/compiler.h
    lib/pud/wireformat/include/OlsrdPudWireFormat/nodeIdConversion.h
    lib/pud/wireformat/include/OlsrdPudWireFormat/wireFormat.h
    lib/pud/wireformat/src/nodeIdConversion.c
    lib/pud/wireformat/src/wireFormat.c
    lib/pud/wireformat-java/resources/WireFormatConstants.java.h
    lib/pud/wireformat-java/src/main/c/org_olsr_plugin_pud_ClusterLeader.c
    lib/pud/wireformat-java/src/main/c/org_olsr_plugin_pud_PositionUpdate.c
    lib/pud/wireformat-java/src/main/c/org_olsr_plugin_pud_UplinkMessage.c
    lib/pud/wireformat-java/src/main/c/util.h
    lib/quagga/src/client.c
    lib/quagga/src/client.h
    lib/quagga/src/common.h
    lib/quagga/src/olsrd_plugin.c
    lib/quagga/src/packet.c
    lib/quagga/src/packet.h
    lib/quagga/src/parse.c
    lib/quagga/src/parse.h
    lib/quagga/src/plugin.c
    lib/quagga/src/plugin.h
    lib/quagga/src/quagga.c
    lib/quagga/src/quagga.h
    lib/secure/src/md5.c
    lib/secure/src/md5.h
    lib/secure/src/olsrd_plugin.c
    lib/secure/src/olsrd_secure.c
    lib/secure/src/olsrd_secure.h
    lib/secure/src/secure_messages.h
    lib/sgwdynspeed/src/configuration.c
    lib/sgwdynspeed/src/configuration.h
    lib/sgwdynspeed/src/olsrdPlugin.c
    lib/sgwdynspeed/src/olsrdPlugin.h
    lib/sgwdynspeed/src/sgwDynSpeed.c
    lib/sgwdynspeed/src/sgwDynSpeed.h
    lib/sgwdynspeed/src/speedFile.c
    lib/sgwdynspeed/src/speedFile.h
    lib/txtinfo/src/olsrd_plugin.c
    lib/txtinfo/src/olsrd_plugin.h
    lib/txtinfo/src/olsrd_txtinfo.c
    lib/txtinfo/src/olsrd_txtinfo.h
    lib/watchdog/src/olsrd_plugin.c
    lib/watchdog/src/olsrd_plugin.h
    src/bsd/apm.c
    src/bsd/dummy.c
    src/bsd/kernel_routes.c
    src/bsd/net.c
    src/cfgparser/cfgfile_gen.c
    src/cfgparser/olsrd_conf.c
    src/cfgparser/olsrd_conf.h
    src/cfgparser/oparse.c
    src/cfgparser/oparse.h
    src/cfgparser/oscan.c
    src/common/autobuf.c
    src/common/autobuf.h
    src/common/avl.c
    src/common/avl.h
    src/common/list.c
    src/common/list.h
    src/linux/apm.c
    src/linux/kernel_routes_nl.c
    src/linux/kernel_tunnel.c
    src/linux/lq_plugin_ffeth_nl80211.c
    src/linux/lq_plugin_ffeth_nl80211.h
    src/linux/net.c
    src/linux/nl80211_link_info.c
    src/linux/nl80211_link_info.h
    src/olsr_switch/commands.h
    src/olsr_switch/link_rules.c
    src/olsr_switch/link_rules.h
    src/olsr_switch/main.c
    src/olsr_switch/ohs_cmd.c
    src/olsr_switch/ohs_cmd.h
    src/olsr_switch/olsr_host_switch.h
    src/unix/ifnet.c
    src/unix/log.c
    src/unix/misc.c
    src/win32/arpa/inet.h
    src/win32/ce/ws2tcpip.h
    src/win32/compat/sys/time.h
    src/win32/net/if.h
    src/win32/net/route.h
    src/win32/netinet/in.h
    src/win32/sys/ioctl.h
    src/win32/sys/socket.h
    src/win32/sys/times.h
    src/win32/sys/utsname.h
    src/win32/apm.c
    src/win32/compat.c
    src/win32/compat.h
    src/win32/dlfcn.h
    src/win32/dummy.c
    src/win32/ifnet.c
    src/win32/kernel_routes.c
    src/win32/log.c
    src/win32/misc.c
    src/win32/net.c
    src/win32/unistd.h
    src/apm.h
    src/build_msg.c
    src/build_msg.h
    src/builddata.c
    src/builddata.h
    src/cli.c
    src/cli.h
    src/defs.h
    src/duplicate_handler.c
    src/duplicate_handler.h
    src/duplicate_set.c
    src/duplicate_set.h
    src/egressFile.c
    src/egressFile.h
    src/egressTypes.h
    src/fpm.c
    src/fpm.h
    src/gateway.c
    src/gateway.h
    src/gateway_costs.c
    src/gateway_costs.h
    src/gateway_default_handler.c
    src/gateway_default_handler.h
    src/gateway_list.c
    src/gateway_list.h
    src/generate_msg.c
    src/generate_msg.h
    src/hashing.c
    src/hashing.h
    src/hna_set.c
    src/hna_set.h
    src/hysteresis.c
    src/hysteresis.h
    src/ifnet.h
    src/interfaces.c
    src/interfaces.h
    src/ipc_frontend.c
    src/ipc_frontend.h
    src/ipcalc.c
    src/ipcalc.h
    src/kernel_routes.h
    src/kernel_tunnel.h
    src/link_set.c
    src/link_set.h
    src/lock_file.c
    src/lock_file.h
    src/log.h
    src/lq_mpr.c
    src/lq_mpr.h
    src/lq_packet.c
    src/lq_packet.h
    src/lq_plugin.c
    src/lq_plugin.h
    src/lq_plugin_default_ff.c
    src/lq_plugin_default_ff.h
    src/lq_plugin_default_ffeth.c
    src/lq_plugin_default_ffeth.h
    src/lq_plugin_default_float.c
    src/lq_plugin_default_float.h
    src/lq_plugin_default_fpm.c
    src/lq_plugin_default_fpm.h
    src/main.c
    src/mantissa.c
    src/mantissa.h
    src/mid_set.c
    src/mid_set.h
    src/misc.h
    src/mpr.c
    src/mpr.h
    src/mpr_selector_set.c
    src/mpr_selector_set.h
    src/neighbor_table.c
    src/neighbor_table.h
    src/net_olsr.c
    src/net_olsr.h
    src/net_os.h
    src/olsr.c
    src/olsr.h
    src/olsr_cfg.h
    src/olsr_cookie.c
    src/olsr_cookie.h
    src/olsr_niit.c
    src/olsr_niit.h
    src/olsr_protocol.h
    src/olsr_random.h
    src/olsr_spf.c
    src/olsr_spf.h
    src/olsr_types.h
    src/olsrd_plugin.h
    src/packet.c
    src/packet.h
    src/parser.c
    src/parser.h
    src/pid_file.c
    src/pid_file.h
    src/plugin_loader.c
    src/plugin_loader.h
    src/plugin_util.c
    src/plugin_util.h
    src/process_package.c
    src/process_package.h
    src/process_routes.c
    src/process_routes.h
    src/rebuild_packet.c
    src/rebuild_packet.h
    src/routing_table.c
    src/routing_table.h
    src/scheduler.c
    src/scheduler.h
    src/tc_set.c
    src/tc_set.h
    src/two_hop_neighbor_table.c
    src/two_hop_neighbor_table.h src/local_gps.c src/local_gps.h)

add_executable(olsrd ${SOURCE_FILES})