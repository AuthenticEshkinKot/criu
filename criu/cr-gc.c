#include <stdio.h>
#include <unistd.h>

#include "files-reg.h"
#include "crtools.h"
#include "mount.h"
#include "stats.h"
#include "pstree.h"

static int max_prepare_namespace();

int cr_garbage_collect(void)
{
	if (check_img_inventory() < 0)
		return -1;

	if (collect_remaps_and_regfiles())
		return -1;

	if (max_prepare_namespace())
		return -1;

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
