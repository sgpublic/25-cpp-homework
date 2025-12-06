//
// Created by coder on 12/6/25.
//

#pragma once

#define __SAVE(NAME, TYPE1)                                                        \
    void NAME(const TYPE1& NAME) {                                                 \
        save(#NAME, NAME);                                                         \
    }

#define __READ(NAME, TYPE1, TYPE2, DEFAULT)                                        \
    TYPE1 NAME() {                                                                 \
        return get(#NAME, QVariant(DEFAULT)).to##TYPE2();                          \
    }

#define SETTING_MEMBER(NAME, TYPE1, TYPE2, DEFAULT)                                \
    Q_INVOKABLE __SAVE(NAME, TYPE1)                                                \
    Q_INVOKABLE __READ(NAME, TYPE1, TYPE2, DEFAULT)

#define SETTING_READONLY(NAME, TYPE1, TYPE2, DEFAULT)                              \
    __SAVE(NAME, TYPE1)                                                            \
    Q_INVOKABLE __READ(NAME, TYPE1, TYPE2, DEFAULT)

#define SETTING_INTERNAL(NAME, TYPE1, TYPE2, DEFAULT)                              \
    __SAVE(NAME, TYPE1)                                                            \
    __READ(NAME, TYPE1, TYPE2, DEFAULT)
