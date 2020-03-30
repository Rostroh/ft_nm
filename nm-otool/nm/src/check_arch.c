/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rostroh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:06:45 by rostroh           #+#    #+#             */
/*   Updated: 2020/03/10 11:27:33 by rostroh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			check_arch32(t_file_inf file, uint32_t cputype, uint32_t fat_idx)
{
	uint32_t				i;
	int						off;
	struct fat_header		hdr;
	struct fat_arch			arch;

	i = 0;
	read_header_fat(&hdr, file.content, sizeof(struct fat_header), file.cig);
	off = sizeof(struct fat_header);
	while (i < hdr.nfat_arch)
	{
		read_arch32(&arch, file.content + off, sizeof(struct fat_arch), \
				file.cig);
		if ((cputype & CPU_ARCH_MASK) == (arch.cputype & CPU_ARCH_MASK) && \
				(cputype & swap_u32(CPU_ARCH_ABI64)) == 0x0 && \
		(arch.cputype & swap_u32(CPU_ARCH_ABI64)) == swap_u32(CPU_ARCH_ABI64))
			return (0);
		if (i < fat_idx && cputype == (uint32_t)arch.cputype)
			return (0);
		off += sizeof(struct fat_arch);
		i++;
	}
	return (1);
}

int			check_arch64(t_file_inf file, uint32_t cputype, uint32_t fat_idx)
{
	uint32_t				i;
	int						off;
	struct fat_header		hdr;
	struct fat_arch_64		arch;

	i = 0;
	read_header_fat(&hdr, file.content, sizeof(struct fat_header), file.cig);
	off = sizeof(struct fat_header);
	while (i < hdr.nfat_arch)
	{
		read_arch64(&arch, file.content + off, sizeof(struct fat_arch_64), \
				file.cig);
		if ((cputype & CPU_ARCH_MASK) == (arch.cputype & CPU_ARCH_MASK) && \
				(cputype & swap_u32(CPU_ARCH_ABI64)) == 0x0 && \
		(arch.cputype & swap_u32(CPU_ARCH_ABI64)) == swap_u32(CPU_ARCH_ABI64))
			return (0);
		if (i < fat_idx && cputype == (uint32_t)arch.cputype)
			return (0);
		off += sizeof(struct fat_arch_64);
		i++;
	}
	return (1);
}
