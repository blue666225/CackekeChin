#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

/// <summary>
/// スプライト
/// </summary>
class Sprite
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	/// <summary>
	/// 頂点データ構造体
	/// </summary>
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

public: // 静的メンバ関数

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <returns>成否</returns>
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texnumber">テクスチャ番号</param>
	/// <param name="filename">画像ファイル名</param>
	/// <returns>成否</returns>
	static bool LoadTexture(UINT texnumber, const wchar_t*filename);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="anchorpoint">アンカーポイント</param>
	/// <param name="isFlipX">左右反転</param>
	/// <param name="isFlipY">上下反転</param>
	/// <returns>生成されたスプライト</returns>
	static Sprite* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

private: // 静的メンバ変数
	// テクスチャの最大枚数
	static const int srvCount = 512;
	// 頂点数
	static const int vertNum = 4;
	// デバイス
	static ID3D12Device* device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	// 射影行列
	static XMMATRIX matProjection;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[srvCount];

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize();

	/// <summary>
	/// 角度の設定
	/// </summary>
	/// <param name="rotation">角度</param>
	void SetRotation(float rotation);

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT2 position);
	
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="size">サイズ</param>
	void SetSize(XMFLOAT2 size);

	/// <summary>
	/// アンカーポイントの設定
	/// </summary>
	/// <param name="anchorpoint">アンカーポイント</param>
	void SetAnchorPoint(XMFLOAT2 anchorpoint);

	/// <summary>
	/// 左右反転の設定
	/// </summary>
	/// <param name="isFlipX">左右反転</param>
	void SetIsFlipX(bool isFlipX);

	/// <summary>
	/// 上下反転の設定
	/// </summary>
	/// <param name="isFlipX">上下反転</param>
	void SetIsFlipY(bool isFlipY);

	/// <summary>
	/// テクスチャ範囲設定
	/// </summary>
	/// <param name="texBase">テクスチャ左上座標</param>
	/// <param name="texSize">テクスチャサイズ</param>
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// テクスチャ番号
	UINT texNumber = 0; 
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position{};
	// スプライト幅、高さ
	XMFLOAT2 size = { 100.0f, 100.0f };
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0, 0 };
	// ワールド行列
	XMMATRIX matWorld{};		
	// 色
	XMFLOAT4 color = { 1, 1, 1, 1 }; 
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// テクスチャ始点
	XMFLOAT2 texBase = { 0, 0 };
	// テクスチャ幅、高さ
	XMFLOAT2 texSize = { 100.0f, 100.0f };

private: // メンバ関数
	/// <summary>
	/// 頂点データ転送
	/// </summary>
	void TransferVertices();
};

