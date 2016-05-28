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

int cr_garbage_collect(bool show)
{
	if (check_img_inventory() < 0)
		return -1;

	if (collect_remaps_and_regfiles())
		return -1;

	if (prepare_task_entries() < 0)
		return -1;

	if (prepare_pstree())
		return -1;

	if (prepare_mnt_ns())
		return -1;

	if (collect_inet_sockets())
		return -1;

	gc_network(show);

	gc_collected_remaps(show);

	return 0;
}
