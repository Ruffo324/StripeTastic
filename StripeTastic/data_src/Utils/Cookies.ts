export module Cookies {
    export function Set(name: string, value: string, days: number): void {
        let expires: string = "";
        if (days) {
            const date: Date = new Date();
            date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
            expires = `; expires=${date.toUTCString()}`;
        }
        document.cookie = name + "=" + (value || "") + expires + "; path=/";
    }

    export function Get(name: string): string {
        const nameEq: string = name + "=";
        const ca: string[] = document.cookie.split(";");

        for (let i: number = 0; i < ca.length; i++) {
            let c: string = ca[i];
            while (c.charAt(0) === " ")
                c = c.substring(1, c.length);
            if (c.indexOf(nameEq) === 0)
                return c.substring(nameEq.length, c.length);
        }

        return null;
    }

    export function Erase(name: string): boolean {
        if (Get(name) === null)
            return false;

        document.cookie = name + "=; Max-Age=-99999999;";
        return true;
    }
}