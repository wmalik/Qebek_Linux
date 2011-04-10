bin_SCRIPTS        = sebekd.pl sbk_ks_log.pl sbk_diag.pl sbk_viewer.pl init.d/sebekd
bin_PROGRAMS       = sbk_extract
EXTRA_DIST         = sebekd.pl sbk_ks_log.pl sbk_diag.pl sbk_viewer.pl init.d/sebekd
INCLUDES           = @INCLUDES@
sbk_extract_SOURCES = sbk_extract.c sbk_extract.h
sbk_upload.pl:
sbk_ks_log.pl:
sbk_diag.pl:
pkg:	${bin_SCRIPTS} ${bin_PROGRAMS}
	rm -rf pkg
	mkdir pkg
	mkdir -p pkg/usr/sbin/
	mkdir -p pkg/etc/init.d/

	cp sbk_extract    pkg/usr/sbin/
	cp sebekd.pl  pkg/usr/sbin/
	cp sbk_ks_log.pl  pkg/usr/sbin/
	cp sbk_diag.pl    pkg/usr/sbin/

	cp sebekd.sh       pkg/etc/init.d/

	tar -zcvf ./hwpkg-sebekd.tgz -C ./pkg/ .
