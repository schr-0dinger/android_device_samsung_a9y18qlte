#
# Copyright (C) 2022 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# The A9 (2018) launched on Oreo MR1, and the device still reports ro.product.first_api_level=27.
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_o_mr1.mk)

TARGET_BOOT_ANIMATION_RES := 1080

# Inherit some common Lineage stuff
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# Inherit from a9y18qlte device
$(call inherit-product, $(LOCAL_PATH)/device.mk)

PRODUCT_BRAND := samsung
PRODUCT_DEVICE := a9y18qlte
PRODUCT_MANUFACTURER := samsung
PRODUCT_NAME := lineage_a9y18qlte
PRODUCT_MODEL := SM-A920F
PRODUCT_GMS_CLIENTID_BASE := android-samsung

TARGET_VENDOR := samsung
TARGET_VENDOR_PRODUCT_NAME := a9y18qlte

# Report the stock Samsung fingerprint rather than a custom-build one.
PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="a9y18qltexx-user 10 QP1A.190711.020 A920FXXS7CVI9 release-keys"

BUILD_FINGERPRINT := "samsung/a9y18qltexx/a9y18qlte:10/QP1A.190711.020/A920FXXS7CVI9:user/release-keys"
