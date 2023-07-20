import * as UE from "ue"
import * as cpp from "cpp"
import { ITSObject } from "./ITSObject";

export class TSNPC implements ITSObject {
    OnCreate(ID: number): boolean {
        return true;
    }
}