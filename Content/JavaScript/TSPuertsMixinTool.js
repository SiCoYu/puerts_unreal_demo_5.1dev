"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.TSPuertsMixinTool = void 0;
const puerts_1 = require("puerts");
class MIXIN_TOOL {
    static LOG_TAG = "[MixinTool] ";
}
;
class TSPuertsMixinTool {
    mixin_map = null;
    /**
     * 初始化MixinTool
     */
    Initialize() {
        if (this.mixin_map == null) {
            this.mixin_map = new Map();
        }
        console.log('PuertsMixinTool Initialize');
    }
    /**
     * 释放MixinTool
     */
    Deinitialize() {
        if (this.mixin_map) {
            this.UnMixinAll();
        }
        console.log('PuertsMixinTool Deinitialize');
    }
    /**
     * 重载Mixin
     * @param ParentClass
     * @param TSModuleName
     * @param bObjectTakeByNative
     * @param bInherit
     * @param bNoMixinedWarning
     * @param bForceMixin
     * @returns
     */
    Mixin(ParentClass, TSModuleName, bObjectTakeByNative, bInherit, bNoMixinedWarning, bForceMixin) {
        console.log('PuertsMixinTool Mixin');
    }
    /**
     * 重载UnMixin
     * @param TSClassName
     * @returns
     */
    UnMixin(TSClassName) {
        return false;
    }
    /**
     * 重载UnMixinAll
     */
    UnMixinAll() {
        this.mixin_map.forEach((value, key) => {
            puerts_1.blueprint.unmixin(value);
        });
        this.mixin_map.clear();
    }
    /**
     * 是否已经Mixin
     * @param TSModuleName
     * @returns
     */
    HasMixin(TSModuleName) {
        return this.mixin_map && this.mixin_map.has(TSModuleName);
    }
}
exports.TSPuertsMixinTool = TSPuertsMixinTool;
//# sourceMappingURL=TSPuertsMixinTool.js.map