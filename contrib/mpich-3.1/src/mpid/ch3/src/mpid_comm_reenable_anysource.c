/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2011 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "mpidimpl.h"

#undef FUNCNAME
#define FUNCNAME MPID_Comm_reenable_anysource
#undef FCNAME
#define FCNAME MPIU_QUOTE(FUNCNAME)
int MPID_Comm_reenable_anysource(MPID_Comm *comm_ptr, MPID_Group **failed_group_ptr)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Group *group_ptr;
    MPIDI_STATE_DECL(MPID_STATE_MPID_COMM_REENABLE_ANYSOURCE);

    MPIDI_FUNC_ENTER(MPID_STATE_MPID_COMM_REENABLE_ANYSOURCE);

    mpi_errno = MPIR_Comm_group_impl(comm_ptr, &group_ptr);
    if (mpi_errno) MPIU_ERR_POP(mpi_errno);
    
    mpi_errno = MPIR_Group_intersection_impl(group_ptr, MPIDI_Failed_procs_group, failed_group_ptr);
    if (mpi_errno) MPIU_ERR_POP(mpi_errno);
    
    mpi_errno = MPIR_Group_free_impl(group_ptr);
    if (mpi_errno) MPIU_ERR_POP(mpi_errno);
    
    comm_ptr->ch.anysource_enabled = TRUE;

 fn_exit:
    MPIDI_FUNC_EXIT(MPID_STATE_MPID_COMM_REENABLE_ANYSOURCE);
    return mpi_errno;
 fn_fail:
    goto fn_exit;
}
