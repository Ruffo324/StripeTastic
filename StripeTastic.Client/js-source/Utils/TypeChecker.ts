export module TypeChecker {
    /**
     * Checks if any of the arguments is undefined.
     * @param objects Objects to check.
     */
    export function isAnyUndefined(...objects: any[]): boolean {
        return objects.some((obj) => typeof obj === "undefined");
    }
}