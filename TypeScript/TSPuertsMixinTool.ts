/*
 * @Author: yuxikuo yuxikuo@h3d.com.cn
 * @Date: 2023-08-31 21:25:29
 * @LastEditors: yuxikuo yuxikuo@h3d.com.cn
 * @LastEditTime: 2023-09-05 15:16:42
 * @FilePath: \TS_workspace\TsProj\framework\core\mixin\ts_puerts_mixin_tool.ts
 * @Description: Mixin工具，对应C++的PuertsMixinTool单例类
 */
import * as UE from 'ue'
import {argv, blueprint, $Ref, $Nullable} from 'puerts';

class MIXIN_TOOL {
    static LOG_TAG = "[MixinTool] ";
}

export interface TSPuertsMixinTool extends UE.PuertsMixinTool {};
export class TSPuertsMixinTool implements TSPuertsMixinTool {    
    private mixin_map : Map<string, any> = null;

    /**
     * 初始化MixinTool
     */
    Initialize(): void {
        if(this.mixin_map == null){
            this.mixin_map = new Map();
        }
        console.log('PuertsMixinTool Initialize')
    }

    /**
     * 释放MixinTool
     */
    Deinitialize(): void {
        if(this.mixin_map){
            this.UnMixinAll();   
        }
        console.log('PuertsMixinTool Deinitialize')
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
    Mixin(ParentClass: $Nullable<UE.Class>, TSModuleName: string, bObjectTakeByNative: boolean, bInherit: boolean, bNoMixinedWarning: boolean, bForceMixin: boolean): void {
        console.log('PuertsMixinTool Mixin')
    }

    /**
     * 重载UnMixin
     * @param TSClassName 
     * @returns 
     */
    UnMixin(TSClassName: string): boolean {
        return false;
    }

    /**
     * 重载UnMixinAll
     */
    UnMixinAll(): void {
        this.mixin_map.forEach((value , key) =>{
            blueprint.unmixin(value);   
        });
        this.mixin_map.clear();
    }

    /**
     * 是否已经Mixin
     * @param TSModuleName 
     * @returns 
     */
    HasMixin(TSModuleName: string): boolean {
        return this.mixin_map && this.mixin_map.has(TSModuleName);
    }
}