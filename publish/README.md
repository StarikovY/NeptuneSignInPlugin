---
title: SignPlugin
description: Sign data, login and verify signature.
---
<!--
# license: Licensed to the Apache Software Foundation (ASF) under one
#         or more contributor license agreements.  See the NOTICE file
#         distributed with this work for additional information
#         regarding copyright ownership.  The ASF licenses this file
#         to you under the Apache License, Version 2.0 (the
#         "License"); you may not use this file except in compliance
#         with the License.  You may obtain a copy of the License at
#
#           http://www.apache.org/licenses/LICENSE-2.0
#
#         Unless required by applicable law or agreed to in writing,
#         software distributed under the License is distributed on an
#         "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#         KIND, either express or implied.  See the License for the
#         specific language governing permissions and limitations
#         under the License.
-->

# neptune-sign-plugin

This plugin implements a data signing API allowing to login and verify signature.

## Installation

    cordova plugin add neptune-sign-plugin

## Supported Platforms

- Windows*

## List of Errors raised by plugin
When an error is thrown, one of these messages will be used:

| ERRORS                            |
|-----------------------------------|
|    Unable to sign data            |
|    Unable to login                |
|    Unable to verify signature     |
|				    |

## Signing Data: Signing data sample <a name="signdata"></a>

The File plugin allows you to sign data. The code snippets in this section demonstrate this task:

```js

cordova.exec(success, errorstop, "SignPlugin", "signMethod", [signer, datatosign, true]);

```

## Login: Login sample <a name="login"></a>

The File plugin allows you to sign data. The code snippets in this section demonstrate this task:

```js

cordova.exec(success, errorstop, "SignPlugin", "loginMethod", [signer]);

```

## Verify Signature: Verify Signaturesample <a name="verify"></a>

The File plugin allows you to verify signed data. The code snippets in this section demonstrate this task:

```js

cordova.exec(success, errorstop, "SignPlugin", "verifyMethod", [signer, signeddata, signature]);

```

