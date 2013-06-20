/*****************************************************************************\
 *  jobacct_gather_linux_common.h - slurm job accounting gather plugin for linux.
 *****************************************************************************
 *  Copyright (C) 2005 Hewlett-Packard Development Company, L.P.
 *  Written by Andy Riebs, <andy.riebs@hp.com>, who borrowed heavily
 *  from other parts of SLURM, and Danny Auble, <da@llnl.gov>
 *  CODE-OCEC-09-009. All rights reserved.
 *
 *  This file is part of SLURM, a resource management program.
 *  For details, see <http://www.schedmd.com/slurmdocs/>.
 *  Please also read the included file: DISCLAIMER.
 *
 *  SLURM is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  In addition, as a special exception, the copyright holders give permission
 *  to link the code of portions of this program with the OpenSSL library under
 *  certain conditions as described in each individual source file, and
 *  distribute linked combinations including the two. You must obey the GNU
 *  General Public License in all respects for all of the code used other than
 *  OpenSSL. If you modify file(s) with this exception, you may extend this
 *  exception to your version of the file(s), but you are not obligated to do
 *  so. If you do not wish to do so, delete this exception statement from your
 *  version.  If you delete this exception statement from all source files in
 *  the program, then also delete it here.
 *
 *  SLURM is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with SLURM; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 *
 *  This file is patterned after jobcomp_linux.c, written by Morris Jette and
 *  Copyright (C) 2002 The Regents of the University of California.
\*****************************************************************************/

#ifndef _JOBACCT_GATHER_LINUX_COMMON_H
#define _JOBACCT_GATHER_LINUX_COMMON_H

#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include "src/common/slurm_xlator.h"
#include "src/common/slurm_jobacct_gather.h"
#include "src/common/slurm_protocol_api.h"
#include "src/common/slurm_protocol_defs.h"
#include "src/common/slurm_acct_gather_energy.h"
#include "src/slurmd/common/proctrack.h"

/* Other useful declarations */

typedef struct prec {	/* process record */
	pid_t	pid;
	pid_t	ppid;
	int     usec;   /* user cpu time */
	int     ssec;   /* system cpu time */
	int     pages;  /* pages */
	int	rss;	/* rss */
	int	vsize;	/* virtual size */
	int	act_cpufreq;	/* actual average cpu frequency */
	int	last_cpu;	/* last cpu */
} prec_t;

static DIR  *slash_proc = NULL;
static pthread_mutex_t reading_mutex = PTHREAD_MUTEX_INITIALIZER;
static int cpunfo_frequency = 0;

/* Finally, pre-define all local routines. */

static void _destroy_prec(void *object);
static int  _is_a_lwp(uint32_t pid);
static void _get_offspring_data(List prec_list, prec_t *ancestor, pid_t pid);
static int  _get_process_data_line(int in, prec_t *prec);
static int  _get_process_statm_line(int in, prec_t *prec);
static int _get_sys_interface_freq_line(uint32_t cpu, char *filename,
					char *sbuf );
static uint32_t _update_weighted_freq(struct jobacctinfo *jobacct,
				      char * sbuf);
bool _use_shared(void);

#endif
