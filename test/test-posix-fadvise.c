/*
 * Copyright (C) 2013-2017 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * This code is a complete clean re-write of the stress tool by
 * Colin Ian King <colin.king@canonical.com> and attempts to be
 * backwardly compatible with the stress tool by Amos Waterland
 * <apw@rossby.metr.ou.edu> but has more stress tests and more
 * functionality.
 *
 */

#include <unistd.h>
#include <fcntl.h>

       int posix_fadvise(int fd, off_t offset, off_t len, int advice);

#define NO_FADV

int main(void)
{
	static const char *filename = "/tmp/test-msync.tmp";
	int fd, ret, err = 1;
	void *ptr;

	fd = open(filename, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		goto err;
	(void)unlink(filename);

#if defined(POSIX_FADV_NORMAL)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_NORMAL);
	(void)ret;
#endif
#if defined(POSIX_FADV_SEQUENTIAL)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_SEQUENTIAL);
	(void)ret;
#endif
#if defined(POSIX_FADV_RANDOM)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_RANDOM);
	(void)ret;
#endif
#if defined(POSIX_FADV_NOREUSE)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_NOREUSE);
	(void)ret;
#endif
#if defined(POSIX_FADV_WILLNEED)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_WILLNEED);
	(void)ret;
#endif
#if defined(POSIX_FADV_DONTNEED)
#undef NO_FADV
	ret = posix_fadvise(fd, 0, 1024, POSIX_FADV_DONTNEED);
	(void)ret;
#endif

#if defined(NO_FADV)
#error no POSIX_FADV advice macros defined!
#endif

err:
	(void)close(fd);

	return err;
}