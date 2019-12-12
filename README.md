1、新建HIDL文件
   1> 在hardware/interfaces目录下新建 naruto/1.0/default目录，并在naruto/1.0目录下新建文件
	   INaruto.hal  types.hal

   2>执行如下指令，生成相关文件
	PACKAGE=android.hardware.naruto@1.0
	LOC=hardware/interfaces/naruto/1.0/default/
	hidl-gen -o $LOC -Lc++-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport $PACKAGE
	hidl-gen -o $LOC -Landroidbp-impl -randroid.hardware:hardware/interfaces -randroid.hidl:system/libhidl/transport $PACKAGE

	3>生成编译makefile
	./hardware/interfaces/update-makefiles.sh
	
	4>再添加两个文件
	touch hardware/interfaces/naruto/1.0/default/android.hardware.naruto@1.0-service.rc
	touch hardware/interfaces/naruto/1.0/default/service.cpp	
   
	目录结构如下：
	.
└── 1.0
    ├── Android.bp
    ├── default
    │   ├── Android.bp
    │   ├── android.hardware.naruto@1.0-service.rc
    │   ├── Naruto.cpp
    │   ├── Naruto.h
    │   └── service.cpp
    ├── INaruto.hal
    └── types.hal

	2、选择HIDL实现方式
	使用USE_BINDERIZED宏控制:	

	修改见代码
	


   3、修改android.bp和rc文件
	@default/Android.bp
	cc_binary {
    name: "android.hardware.naruto@1.0-service",
    defaults: ["hidl_defaults"],
    proprietary: true,
    relative_install_path: "hw",
    srcs: ["service.cpp"],
    init_rc: ["android.hardware.naruto@1.0-service.rc"],

    shared_libs: [
            "libhidlbase",
            "libhidltransport",
            "libutils",
            "liblog",
            "android.hardware.naruto@1.0",
        ],
	}

	@android.hardware.naruto@1.0-service.rc
	service naruto_hal_service /vendor/bin/hw/android.hardware.naruto@1.0-service
    class hal
    user system
    group system

	4、编译
	mmm hardware/interface/naruto
	执行后生成如下文件：
system/lib/android.hardware.naruto@1.0.so
system/lib/android.hardware.naruto@1.0-adapter-helper.so
system/lib/vndk-28/android.hardware.naruto@1.0.so
system/framework/android.hardware.naruto-V1.0-java.jar
system/framework/oat/arm/android.hardware.naruto-V1.0-java.odex
system/framework/oat/arm/android.hardware.naruto-V1.0-java.vdex
vendor/bin/hw/android.hardware.naruto@1.0-service
vendor/bin/narutotest
vendor/etc/init/android.hardware.naruto@1.0-service.rc
vendor/lib/hw/android.hardware.naruto@1.0-impl.so
vendor/lib/android.hardware.naruto@1.0-adapter-helper.so

    5、修改manifest
	 在manifest文件里添加vendor接口的定义，不然在client端是没法拿到service的，在相应的manifest.xml里面加入。
	 现在所使用的项目在device/sprd/pike2/common/manifest_main.xml键入
+    <hal format="hidl">
+        <name>android.hardware.naruto</name>
+        <transport>hwbinder</transport>
+        <impl level="generic"></impl>
+        <version>1.0</version>
+        <interface>
+            <name>INaruto</name>
+            <instance>default</instance>
+        </interface>
+    </hal>
	
	修改见：01_manifest_main.diff

    6、修改sepolicy
	修改见：02_sepolicy.diff hal_naruto_default.te


全部修改完成后，需要工程全编

7、编写测试程序
	文件见：narutotest


遇到的问题：
1、编译报错
报错信息：error: VNDK library list has been changed.

解决办法：
比对out/target/product/k150/obj/PACKAGING/vndk_intermediates/libs.txt文件与build/make/target/product/vndk/current.txt、28.txt文件的差异，复制到current.txt、28.txt文件中；
然后删除掉out/target/product/k150/obj/PACKAGING/vndk_intermediates/libs.txt。





