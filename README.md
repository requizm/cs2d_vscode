</br>
__GCC:__ 9.2.0 </br>
__Target:__ win32

</br></br></br>

**~~Önemli Not:~~**
~~Build edecekseniz, cmake kullanmayın. Build için oluşturduğum makefile’ı kullanın. Cmake kullanma amacım ise Travis CI. Nedeni şu:
Mingw-64 paketindeki bazı kütüphaneler uyumluluk sorunu çıkartıyor. Kendi bilgisayarımda bu sorunu, “exception: sjlj” şeklinde yükleyerek düzeltiyorum ama bulut bilgisayardaki pakete dokunamıyorum maalesef. O yüzden cmake’in görevi, 64 bit build edilebilir makefile dosyası oluşturmak. Travis CI oradaki makefile’ı build ediyor yani. Docker ile de bu sorunu çözebilirdim ama hiç ona bulaşmak istemiyorum.~~
</br>
</br>
**~~Note:~~**
~~If you are make a build, don’t use cmake. Use the makefile I created for build. My purpose to use Cmake is Travis CI. The reason is this:
Some libraries in the mingw-64 package present compatibility issues. On my own computer, I fix this problem by installing “exception: sjlj”, but unfortunately i cannot touch the package on the cloud computer. That’s why cmake’s task is to create a 64 bit buildable makefile file. Travis CI is building the makefile over there. I could solve this problem with Docker, but I don’t want to deal with it at all.~~
