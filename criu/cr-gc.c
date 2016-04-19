#include <stdio.h>
#include <unistd.h>

#include "files-reg.h"
#include "crtools.h"
#include "mount.h"
#include "stats.h"

#ifndef arch_export_restore_thread
#define arch_export_restore_thread	__export_restore_thread
#endif

#ifndef arch_export_restore_task
#define arch_export_restore_task	__export_restore_task
#endif

#ifndef arch_export_unmap
#define arch_export_unmap		__export_unmap
#endif

static int max_prepare_namespace();

int cr_garbage_collect(void)
{
	/*if (cr_plugin_init(CR_PLUGIN_STAGE__RESTORE))
		return -1;*/

	/*if (check_img_inventory() < 0)
		return -1;*/

	if (init_stats(RESTORE_STATS)) //мб нужны GC_STATS
		return -1;

	/*if (kerndat_init_rst())
		return -1;*/

	timing_start(TIME_RESTORE);

	/*if (cpu_init() < 0)
		return -1;

	if (vdso_init())
		return -1;

	if (opts.cpu_cap & (CPU_CAP_INS | CPU_CAP_CPU)) {
		if (cpu_validate_cpuinfo())
			return -1;
	}*/


	if (collect_remaps_and_regfiles())
		return -1;
	printf("collected remaps and regfiles\n");


  if (max_prepare_namespace())
    return -1;


  if (delete_remaps())
		return -1;

	return 0;
}

static int max_prepare_namespace()
{  
	pr_info("MAX: going to prepare_namespace\n");
	/*if (prepare_namespace(current, ca.clone_flags)) //нужно для unlink
			return -1;*/

	//корректна ли замена prepare_namespace на prepare_mnt_ns?
	if (prepare_mnt_ns())
		return -1;

  return 0;
}
