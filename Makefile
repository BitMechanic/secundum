CC=g++
CFLAGS=-I$(POLYCODE)/Release/Linux/Framework/Core/Dependencies/include -I$(POLYCODE)/Release/Linux/Framework/Core/Dependencies/include/AL -I$(POLYCODE)/Release/Linux/Framework/Core/include -I$(POLYCODE)/Release/Linux/Framework/Modules/include -I$(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/include -I$(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread $(POLYCODE)/Release/Linux/Framework/Core/lib/libPolycore.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/libfreetype.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/liblibvorbisfile.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/liblibvorbis.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/liblibogg.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/libopenal.so $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/libphysfs.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/libpng15.a $(POLYCODE)/Release/Linux/Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL $(POLYCODE)/Release/Linux/Framework/Modules/lib/libPolycode2DPhysics.a $(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/lib/libBox2D.a $(POLYCODE)/Release/Linux/Framework/Modules/lib/libPolycode3DPhysics.a $(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/lib/libBulletDynamics.a $(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/lib/libBulletCollision.a $(POLYCODE)/Release/Linux/Framework/Modules/Dependencies/lib/libLinearMath.a /usr/lib/x86_64-linux-gnu/libX11.so.6 $(POLYCODE)/Release/Linux/Framework/Modules/lib/libPolycodeUI.a $(POLYCODE)/Release/Linux/Framework/Core/lib/libPolycore.a

default: basicMotion

clean:
	rm basicMotion

basicMotion: Examples/basicMotion/*.cpp Examples/basicMotion/*.h
	$(CC) $(CFLAGS) Examples/basicMotion/*.cpp -o basicMotion $(LDFLAGS) -O3
