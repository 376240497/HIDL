#include <android/hardware/naruto/1.0/INaruto.h>
#include <hidl/Status.h>
#include <hidl/LegacySupport.h>
#include <utils/misc.h>
#include <hidl/HidlSupport.h>
#include <stdio.h>

using android::hardware::naruto::V1_0::INaruto;
using android::hardware::naruto::V1_0::Person;
using android::sp;
using android::hardware::hidl_string;

Person mPerson;

INaruto::getPersonInfo_cb get_person_info(Person person) {
	mPerson = person;

	return nullptr;
}

int main()
{

    android::sp<INaruto> service = INaruto::getService();
    if(service == nullptr) {
        printf("Failed to get service\n");
        return -1;
    }

    service->helloWorld("paul.liao", [&](hidl_string result) {
                printf("%s\n", result.c_str());
        });

	service->getPersonInfo(get_person_info);

	printf("name: %s, age = %d, sex = %s\n", mPerson.name.c_str(), 
		mPerson.age, mPerson.sex.c_str());

    return 0;
}
