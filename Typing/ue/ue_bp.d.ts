/// <reference path="puerts.d.ts" />
declare module "ue" {
    import {$Ref, $Nullable} from "puerts"

    import * as cpp from "cpp"

    import * as UE from "ue"

// __TYPE_DECL_START: C58A3A0E40D89448FD8D8EAD08684AB7
    namespace Game.BP_StoryTrigger {
        class BP_StoryTrigger_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_StoryTrigger_C;
            static Load(InName: string): BP_StoryTrigger_C;
        
            __tid_BP_StoryTrigger_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 21D0BB064BBB7F7909AFD88E31BE4032
    namespace Game.BP_StoryNPC {
        class BP_StoryNPC_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_StoryNPC_C;
            static Load(InName: string): BP_StoryNPC_C;
        
            __tid_BP_StoryNPC_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 54084F3F4C351B07B4EBAE8A0DB9ABED
    namespace Game.BP_ManualBindActor {
        class BP_ManualBindActor_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_ManualBindActor_C;
            static Load(InName: string): BP_ManualBindActor_C;
        
            __tid_BP_ManualBindActor_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: F49654174DF11A670C542687CFE20F02
    namespace Game.BP_AutoBindActor {
        class BP_AutoBindActor_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            DefaultSceneRoot: UE.SceneComponent;
            GetTSModuleName() : string;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): BP_AutoBindActor_C;
            static Load(InName: string): BP_AutoBindActor_C;
        
            __tid_BP_AutoBindActor_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2620B05B4D570B271A8AAF934441D4E7
    namespace Game.StarterContent.TestWidgetBlueprint {
        class TestWidgetBlueprint_C extends UE.UserWidget {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            Button1: UE.Button;
            TextBox: UE.MultiLineEditableTextBox;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TestWidgetBlueprint_C;
            static Load(InName: string): TestWidgetBlueprint_C;
        
            __tid_TestWidgetBlueprint_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: C9B8A43E442C8D87E5B77BB284D93163
    namespace Game.StarterContent.TestStruct {
        class TestStruct {
            constructor();
            constructor(speed: number, age: number);
            speed: number;
            age: number;
            /**
             * @deprecated use StaticStruct instead.
             */
            static StaticClass(): ScriptStruct;
            static StaticStruct(): ScriptStruct;
            __tid_TestStruct_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 59ADD20544E242E59B518787A6F8F288
    namespace Game.StarterContent.TestEnum {
        enum TestEnum { Blue, Red, Green, TestEnum_MAX, __typeKeyDoNoAccess}
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: A5C7E431443721484614F0A5183DEBCD
    namespace Game.StarterContent.TestBlueprint {
        class TestBlueprint_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            B1: boolean;
            I1: number;
            I2: number;
            Bar(NewParam: UE.Game.StarterContent.TestStruct.TestStruct) : void;
            ExecuteUbergraph_TestBlueprint(EntryPoint: number) : void;
            Foo(P1: boolean, P2: number, P3: number) : void;
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): TestBlueprint_C;
            static Load(InName: string): TestBlueprint_C;
        
            __tid_TestBlueprint_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 8C3BD456442ED5244F46E2A37BF5ECB7
    namespace Game.StarterContent.MixinTest {
        class MixinTest_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            ExecuteUbergraph_MixinTest(EntryPoint: number) : void;
            Log(P: string) : void;
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MixinTest_C;
            static Load(InName: string): MixinTest_C;
        
            __tid_MixinTest_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 2BDEF8114014B8B86032D4A518847312
    namespace Game.StarterContent.MixinSuperTestDerived {
        class MixinSuperTestDerived_C extends UE.Game.StarterContent.MixinSuperTestBase.MixinSuperTestBase_C {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            Foo() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MixinSuperTestDerived_C;
            static Load(InName: string): MixinSuperTestDerived_C;
        
            __tid_MixinSuperTestDerived_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
// __TYPE_DECL_START: 33357AC6463C3AB157426D9264E94557
    namespace Game.StarterContent.MixinSuperTestBase {
        class MixinSuperTestBase_C extends UE.Actor {
            constructor(Outer?: Object, Name?: string, ObjectFlags?: number);
            UberGraphFrame: UE.PointerToUberGraphFrame;
            DefaultSceneRoot: UE.SceneComponent;
            ExecuteUbergraph_MixinSuperTestBase(EntryPoint: number) : void;
            Foo() : void;
            ReceiveBeginPlay() : void;
            static StaticClass(): Class;
            static Find(OrigInName: string, Outer?: Object): MixinSuperTestBase_C;
            static Load(InName: string): MixinSuperTestBase_C;
        
            __tid_MixinSuperTestBase_C_0__: boolean;
        }
        
    }

// __TYPE_DECL_END
}
