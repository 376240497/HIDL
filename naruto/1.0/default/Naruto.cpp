#include "Naruto.h"

namespace android {
namespace hardware {
namespace naruto {
namespace V1_0 {
namespace implementation {

// Methods from ::android::hardware::naruto::V1_0::INaruto follow.
Return<void> Naruto::helloWorld(const hidl_string& name, helloWorld_cb _hidl_cb) {
    // TODO implement

	char buf[128];
	::memset(buf, 0, 128);
	::snprintf(buf, 128, "helloworld, %s", name.c_str());
	hidl_string result(buf);

	_hidl_cb(result);
	

    return Void();
}

Return<void> Naruto::getPersonInfo(getPersonInfo_cb _hidl_cb) {
    // TODO implement

	Person person;
	person.age = 12;
	person.name = "naruto";
	person.sex = "man";

	_hidl_cb(person);

    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

INaruto* HIDL_FETCH_INaruto(const char* /* name */) {
    return new Naruto();
}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace naruto
}  // namespace hardware
}  // namespace android
