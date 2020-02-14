# cs2d_vscode
 
<a href="https://scan.coverity.com/projects/requizm-cs2d_vscode">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/20359/badge.svg"/>
</a><br/>

[![Build Status](https://travis-ci.org/requizm/cs2d_vscode.svg?branch=master)](https://travis-ci.org/requizm/cs2d_vscode)

<br/><br/><br/>

<p>-Windows x86</p>
<p>&nbsp;</p>
<p><strong>&Ouml;nemli Not:</strong><br />Build edecekseniz, cmake kullanmayın. Build i&ccedil;in oluşturduğum makefile'ı kullanın. Cmake kullanma amacım ise Travis CI.&nbsp;Nedeni şu:<br /> Travis CI'ın desteklediği Windows işletim sistemi hen&uuml;z geliştirme aşamasında ve mingw paketinin 64 bit versiyonu y&uuml;kl&uuml;. Benim mingw paketim 32 bit olduğu i&ccedil;in, *.lib dosyalarımın bağlanmasında sıkıntı &ccedil;ıkıyor, build edilemiyor. O y&uuml;zden cmake'in g&ouml;revi, 64 bit build edilebilir makefile dosyası oluşturmak. Travis CI oradaki makefile'ı build ediyor yani. Docker ile de bu sorunu &ccedil;&ouml;zebilirdim ama hi&ccedil; ona bulaşmak istemiyorum.&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><strong>Note:</strong><br />If you are make a build, don't use cmake. Use the makefile I created for build. My purpose to use Cmake is Travis CI. The reason is this:<br />The Windows operating system supported by Travis CI is still under development and a 64-bit version of the mingw package is installed. Since my mingw package is 32 bit, there is a problem connecting my *.lib files, it cannot be built. That's why cmake's task is to create a 64 bit buildable makefile file. Travis CI is building the makefile over there.&nbsp;I could solve this problem with Docker, but I don't want to deal with it at all.</p>
<p>&nbsp;</p>
