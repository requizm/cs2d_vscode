# cs2d_vscode
 
<a href="https://scan.coverity.com/projects/requizm-cs2d_vscode">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/20359/badge.svg"/>
</a><br/>

[![Build Status](https://travis-ci.org/requizm/cs2d_vscode.svg?branch=master)](https://travis-ci.org/requizm/cs2d_vscode)

<br/><br/><br/>

<p>-Windows x86</p>
<p>&nbsp;</p>
<p><strong>&Ouml;nemli Not:</strong><br />Mingw-64 versiyonu 8.X olmamalı. Çünkü filesystem kütüphanesi sorunlu. 7.X kullanabilirsiniz.<br />Build edecekseniz, cmake kullanmayın. Build i&ccedil;in oluşturduğum makefile'ı kullanın. Cmake kullanma amacım ise Travis CI.&nbsp;Nedeni şu:<br />Mingw-64 paketindeki bazı k&uuml;t&uuml;phaneler uyumluluk sorunu &ccedil;ıkartıyor. Kendi bilgisayarımda bu sorunu, "exception: sjlj" şeklinde y&uuml;kleyerek d&uuml;zeltiyorum ama bulut bilgisayardaki pakete dokunamıyorum maalesef. O y&uuml;zden cmake'in g&ouml;revi, 64 bit build edilebilir makefile dosyası oluşturmak. Travis CI oradaki makefile'ı build ediyor yani. Docker ile de bu sorunu &ccedil;&ouml;zebilirdim ama hi&ccedil; ona bulaşmak istemiyorum.&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
<p><strong>Note:</strong><br />The mingw-64 version should not be 8.X. Because the filesystem library is problematic. You can use 7.X.<br />If you are make a build, don't use cmake. Use the makefile I created for build. My purpose to use Cmake is Travis CI. The reason is this:<br />Some libraries in the mingw-64 package present compatibility issues. On my own computer, I fix this problem by installing "exception: sjlj", but unfortunately i cannot touch the package on the cloud computer. That's why cmake's task is to create a 64 bit buildable makefile file. Travis CI is building the makefile over there.&nbsp;I could solve this problem with Docker, but I don't want to deal with it at all.</p>
<p>&nbsp;</p>
