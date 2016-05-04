#include <stdio.h>
#include <unistd.h>

#include "files-reg.h"
#include "crtools.h"
#include "mount.h"
#include "stats.h"
#include "pstree.h"
#include "net.h"
#include "sk-inet.h"
#include "rst-malloc.h"

static int max_prepare_namespace();
static int max_prepare_sockets();

int cr_garbage_collect(bool show)
{
	if (check_img_inventory() < 0)
		return -1;

	if (collect_remaps_and_regfiles())
		return -1;

	if (max_prepare_namespace())
		return -1;

	if (max_prepare_sockets())
		return -1;

	network_rules_deletion(show);

	delete_collected_remaps();

	return 0;
}

static int max_prepare_namespace()
{  
	pr_info("MAX: going to prepare_namespace\n");

	if (prepare_pstree(true))
		return -1;

	if (prepare_mnt_ns())
		return -1;

  return 0;
}

static int max_prepare_sockets()
{
	if (collect_inet_sockets())
		return -1;

	rst_mem_switch_to_private();

	if (rst_tcp_socks_prep())
		return -1;

	return 0;
}
