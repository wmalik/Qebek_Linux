bin_SCRIPTS        = sebekd.pl sbk_ks_log.pl sbk_diag.pl sbk_viewer.pl init.d/sebekd
bin_PROGRAMS       = sbk_extract
EXTRA_DIST         = sebekd.pl sbk_ks_log.pl sbk_diag.pl sbk_viewer.pl init.d/sebekd
INCLUDES           = @INCLUDES@
sbk_extract_SOURCES = sbk_extract.c sbk_extract.h
sbk_upload.pl:
sbk_ks_log.pl:
sbk_diag.pl:
ver=@VERSION@
pname=sebekd
rpm: dist-gzip
	mv ${pname}-${ver}.tar.gz ${HOME}/rpm/SOURCES
	rpmbuild -bb --sign sebekd.spec
	
