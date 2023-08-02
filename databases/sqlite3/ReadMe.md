Theory: 
sudo chown -R luanpham:luanpham /var/calib

Pratical: {https://stackoverflow.com/questions/42407710/chown-r-not-working-in-yocto-project-recipe}
First, chown and chmod should work in YP/OE recipes the way you use them.

The problem may be that you've missed a / in your path arguments for the commands. According to the documentation [1] ${D} has no trailing /.

Therefore the following should work:

do_install() {
  install -d ${D}/${localstatedir}/www
  cp -r ${S}/sources/* ${D}/${localstatedir}/www/
  chown -R www-data:www-data ${D}/${localstatedir}/www/
  chmod -R 775 ${D}/${localstatedir}/www/cgi-bin
}

(If not please post your bitbake logs)

[1] https://www.yoctoproject.org/docs/latest/mega-manual/mega-manual.html#var-D
